#pragma once

#include <winnt.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <json-c/json.h>

// Vibecoded

// Helper: Ensure the "registry" directory exists
void __windows_shim_ensure_directory() {
    struct stat st = {0};
    if (stat("registry", &st) == -1) {
        #ifdef _WIN32
        mkdir("registry");
        #else
        mkdir("registry", 0700);
        #endif
    }
}

// Helper: Construct the file path based on the hive
void __windows_shim_get_hive_filepath(char* buffer, size_t size, const char* hive) {
    snprintf(buffer, size, "registry/%s.json", hive);
}

// Write an HKEY struct to the appropriate JSON file
void __windows_shim_writeJson(HKEY key) {
 	printf("%s\n", key->pathSeperated[0]);
	if (!key || !key->pathSeperated || !key->pathSeperated[0]) {
        fprintf(stderr, "Error: Invalid HKEY or empty pathSeperated[0]\n");
        return;
    }

    __windows_shim_ensure_directory();

    char filepath[512];
    snprintf(filepath, sizeof(filepath), "registry/%s.json", key->pathSeperated[0]);

    struct json_object *root;
    struct json_object *registry_array;

    // Try to load existing file
    root = json_object_from_file(filepath);

    if (root == NULL) {
        // File doesn't exist or is invalid; create a new structure
        root = json_object_new_object();
        registry_array = json_object_new_array();
        json_object_object_add(root, "entries", registry_array);
    } else {
        // File exists, find the "entries" array
        if (!json_object_object_get_ex(root, "entries", &registry_array)) {
            // If the file exists but has no "entries" key, create it
            registry_array = json_object_new_array();
            json_object_object_add(root, "entries", registry_array);
        }
    }

    // Create the entry object
    struct json_object *entry = json_object_new_object();
    json_object_object_add(entry, "path", json_object_new_string(key->path));
    json_object_object_add(entry, "name", json_object_new_string(key->name));
    json_object_object_add(entry, "type", json_object_new_int(key->type));
    json_object_object_add(entry, "value", json_object_new_int64(key->value));

    // Fill pathSeperated array
    struct json_object *path_arr = json_object_new_array();
    for (int i = 0; key->pathSeperated[i] != NULL; i++) {
        json_object_array_add(path_arr, json_object_new_string(key->pathSeperated[i]));
    }
    json_object_object_add(entry, "pathSeperated", path_arr);

    // Add entry to the main array
    json_object_array_add(registry_array, entry);

    // WRITE TO DISK - Check for success
    if (json_object_to_file_ext(filepath, root, JSON_C_TO_STRING_PRETTY) == 0) {
        printf("Successfully wrote to: %s\n", filepath);
    } else {
        fprintf(stderr, "Error: Failed to write to %s\n", filepath);
    }

    // Clean up
    json_object_put(root);
}

// Load values into an HKEY struct if it exists in the JSON (matching by path and name)
int __windows_shim_readJson(HKEY key) {
    if (!key || !key->pathSeperated || !key->pathSeperated[0]) return 0;

    char filepath[256];
    __windows_shim_get_hive_filepath(filepath, sizeof(filepath), key->pathSeperated[0]);

    struct json_object *root = json_object_from_file(filepath);
    if (!root) return 0;

    struct json_object *registry_array;
    if (!json_object_object_get_ex(root, "entries", &registry_array)) {
        json_object_put(root);
        return 0;
    }

    int found = 0;
    size_t n_entries = json_object_array_length(registry_array);
    for (size_t i = 0; i < n_entries; i++) {
        struct json_object *entry = json_object_array_get_idx(registry_array, i);
        struct json_object *j_path, *j_name, *j_type, *j_value;

        json_object_object_get_ex(entry, "path", &j_path);
        json_object_object_get_ex(entry, "name", &j_name);

        // Check if this entry matches the requested path and name
        if (strcmp(json_object_get_string(j_path), key->path) == 0 &&
            strcmp(json_object_get_string(j_name), key->name) == 0) {

            json_object_object_get_ex(entry, "type", &j_type);
            json_object_object_get_ex(entry, "value", &j_value);

            key->type = json_object_get_int(j_type);
            key->value = (uint32_t)json_object_get_int64(j_value);
            found = 1;
            break;
        }
    }

    json_object_put(root);
    return found;
}
