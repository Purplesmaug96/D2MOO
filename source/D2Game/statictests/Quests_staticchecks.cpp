
#include <QUESTS/Quests.h>

#if defined(D2_VERSION_110F) && defined(_WIN32)
static_assert(sizeof(D2QuestDataStrc) == 0xF4, "Size of D2ClientStrc does not match v1.10f");
#endif
