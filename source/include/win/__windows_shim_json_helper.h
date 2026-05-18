#pragma once

#include "winnt.h"

#include <json-c/json.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Vibecoded

// Helper: Ensure the "registry" directory exists
static inline void __windows_shim_ensure_directory() {
	struct stat st = { 0 };
	if (stat("registry", &st) == -1) {
#ifdef _WIN32
		mkdir("registry");
#else
		mkdir("registry", 0700);
#endif
	}
}

// Helper: Construct the file path based on the hive
static inline void __windows_shim_get_hive_filepath(char* buffer, size_t size, const char* hive) {
	snprintf(buffer, size, "registry/%s.json", hive);
}

struct json_object* __windows_shim_get_nested_folder(struct json_object* root, char** folders, int create_if_missing) {
	struct json_object* current = root;
	if (!folders || !folders[0]) {
		return NULL;
	}

	// Start at index 1; index 0 is the Hive/Filename
	for (int i = 1; folders[i] != NULL; i++) {
		struct json_object* next;
		if (!json_object_object_get_ex(current, folders[i], &next)) {
			if (create_if_missing) {
				next = json_object_new_object();
				json_object_object_add(current, folders[i], next);
			} else {
				return NULL;
			}
		}
		current = next;
	}
	return current;
}

static inline void __windows_shim_writeJson(HKEY key) {
	if (!key || !key->pathSeperated || !key->pathSeperated[0]) {
		return;
	}

	__windows_shim_ensure_directory();
	char filepath[256];
	snprintf(filepath, sizeof(filepath), "registry/%s.json", key->pathSeperated[0]);

	struct json_object* root = json_object_from_file(filepath);
	if (!root) {
		root = json_object_new_object();
	}

	// Traverse to the deepest folder
	struct json_object* target_folder = __windows_shim_get_nested_folder(root, key->pathSeperated, 1);

	struct json_object* entries_array;
	if (!json_object_object_get_ex(target_folder, "entries", &entries_array)) {
		entries_array = json_object_new_array();
		json_object_object_add(target_folder, "entries", entries_array);
	}

	// Search for existing entry to update
	struct json_object* entry = NULL;
	int array_len = json_object_array_length(entries_array);
	for (int i = 0; i < array_len; i++) {
		struct json_object* tmp = json_object_array_get_idx(entries_array, i);
		struct json_object* j_name;
		if (json_object_object_get_ex(tmp, "name", &j_name) &&
			strcmp(json_object_get_string(j_name), key->name) == 0) {
			entry = tmp;
			break;
		}
	}

	// Update or Create
	if (!entry) {
		entry = json_object_new_object();
		json_object_object_add(entry, "name", json_object_new_string(key->name));
		json_object_array_add(entries_array, entry);
	}

	json_object_object_add(entry, "type", json_object_new_int(key->type));
	json_object_object_add(entry, "value", json_object_new_int64(key->value));

	json_object_to_file_ext(filepath, root, JSON_C_TO_STRING_PRETTY);
	json_object_put(root);
}

static inline bool __windows_shim_readJson(HKEY key) {
	if (!key || !key->pathSeperated || !key->pathSeperated[0]) {
		return 0;
	}

	char filepath[256];
	snprintf(filepath, sizeof(filepath), "registry/%s.json", key->pathSeperated[0]);

	struct json_object* root = json_object_from_file(filepath);
	if (!root) {
		return 0;
	}

	struct json_object* target_folder = __windows_shim_get_nested_folder(root, key->pathSeperated, 0);
	struct json_object* entries_array;

	if (target_folder && json_object_object_get_ex(target_folder, "entries", &entries_array)) {
		int array_len = json_object_array_length(entries_array);
		for (int i = 0; i < array_len; i++) {
			struct json_object* entry = json_object_array_get_idx(entries_array, i);
			struct json_object* j_name;
			json_object_object_get_ex(entry, "name", &j_name);

			if (strcmp(json_object_get_string(j_name), key->name) == 0) {
				struct json_object *j_type, *j_value;
				json_object_object_get_ex(entry, "type", &j_type);
				json_object_object_get_ex(entry, "value", &j_value);

				key->type = json_object_get_int(j_type);
				key->value = (uint32_t)json_object_get_int64(j_value);
				json_object_put(root);
				return true;
			}
		}
	}

	json_object_put(root);
	return false;
}