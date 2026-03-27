/**
 * @file group.h
 * @author DargoDargonyx
 * @date 03/27/2026
 * @brief Handles the logic for handling groups.
 */

#ifndef GROUP_H
#define GROUP_H

// types
#define G_TYPE_COUNT 3
#define G_TYPE_NONE 0
#define G_TYPE_CLASS 1
#define G_TYPE_DEV 2
#define G_TYPE_RESEARCH 3

// semesters
#define SEM_COUNT 3
#define SEM_NONE 0
#define SEM_FALL 1
#define SEM_SPRING 2
#define SEM_SUMMER 3

// topics
#define TOP_COUNT 4
#define TOP_NONE 0
#define TOP_CHEM 1
#define TOP_CS 2
#define TOP_BIO 3
#define TOP_PHY 4

#include "core/task.h"

typedef struct Group Group;
struct Group {
    void (*destroy)(Group* self);
    char* name;
    int type;
    int taskCap;
    int taskCount;
    Task** tasks;
};

typedef struct {
    Group base;
    int grade;
    int semester;
    int topic;
    int year;
} ClassGroup;

typedef struct {
    Group base;
    int topic;
    int year;
} DevGroup;

typedef struct {
    Group base;
    int topic;
    int year;
} ResearchGroup;

ClassGroup* createClassGroup(const char* n, int sem, int top, int y);
void destroyClassGroup(Group* self);

DevGroup* createDevGroup(const char* n, int top, int y);
void destroyDevGroup(Group* self);

ResearchGroup* createResearchGroup(const char* n, int top, int y);
void destroyResearchGroup(Group* self);

#endif
