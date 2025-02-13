#pragma once

#include "alias.h"
#include "custom_events.h"
#include "graph.h"
#include "group.h"
#include "misc/env_vars.h"
#include "misc/helpers.h"
#include "popup.h"
#include "text.h"

struct bar_item {
  char type;
  char* name;

  // Update Modifiers
  uint32_t counter;
  bool needs_update;
  bool updates;
  bool updates_only_when_shown;
  bool lazy;
  bool selected;
  bool mouse_over;
  bool ignore_association;
  bool overrides_association;

  // Drawing Modifiers
  bool drawing;
  bool has_const_width;
  char align;
  uint32_t custom_width;
  uint32_t blur_radius;

  // These are 32bit masks where the ith bit represents the ith screen/display/bar association
  bool associated_to_active_display;
  uint32_t associated_bar;
  uint32_t associated_display;
  uint32_t associated_space;
  uint32_t update_frequency;

  char* script;
  char* click_script;
  struct signal_args signal_args;
  
  // The position in the bar: l,r,c
  char position;
  int y_offset;

  // Background
  struct background background;

  // Icon properties
  struct text icon;

  // Label properties
  struct text label;

  // Graph Data
  bool has_graph;
  struct graph graph;

  // Alias Data
  bool has_alias;
  struct alias alias;

  // Group Properties
  struct group* group;

  // Update Events
  uint64_t update_mask;

  // Windows
  uint32_t num_windows;
  struct window** windows;

  // Popup
  struct popup popup;
  struct bar_item* parent;

  // Mach
  mach_port_t event_port;
};

struct bar_item* bar_item_create();
void bar_item_inherit_from_item(struct bar_item* bar_item, struct bar_item* ancestor);
void bar_item_init(struct bar_item* bar_item, struct bar_item* default_item);
void bar_item_destroy(struct bar_item* bar_item);

bool bar_item_update(struct bar_item* bar_item, char* sender, bool forced, struct env_vars* env_vars);
bool bar_item_is_shown(struct bar_item* bar_item);

void bar_item_append_associated_space(struct bar_item* bar_item, uint32_t bit);
void bar_item_append_associated_display(struct bar_item* bar_item, uint32_t bit);
void bar_item_append_associated_bar(struct bar_item* bar_item, uint32_t adid);
void bar_item_remove_associated_bar(struct bar_item* bar_item, uint32_t adid);
void bar_item_reset_associated_bar(struct bar_item* bar_item);
void bar_item_set_name(struct bar_item* bar_item, char* name);
void bar_item_set_type(struct bar_item* bar_item, char type);
void bar_item_set_position(struct bar_item* bar_item, char position);
void bar_item_set_script(struct bar_item* bar_item, char* script);
void bar_item_set_click_script(struct bar_item* bar_item, char* script);
bool bar_item_set_drawing(struct bar_item* bar_item, bool state);
bool bar_item_set_yoffset(struct bar_item* bar_item, int offset);
bool bar_item_set_width(struct bar_item* bar_item, int width);

uint32_t bar_item_get_length(struct bar_item* bar_item, bool ignore_override);
uint32_t bar_item_get_height(struct bar_item* bar_item);

void bar_item_needs_update(struct bar_item* bar_item);

void bar_item_on_click(struct bar_item* bar_item, uint32_t type, uint32_t modifier);
void bar_item_mouse_entered(struct bar_item* bar_item);
void bar_item_mouse_exited(struct bar_item* bar_item);

struct window* bar_item_get_window(struct bar_item* bar_item, uint32_t adid);
void bar_item_remove_window(struct bar_item* bar_item, uint32_t adid);
CGRect bar_item_construct_bounding_rect(struct bar_item* bar_item);

CGPoint bar_item_calculate_shadow_offsets(struct bar_item* bar_item);
uint32_t bar_item_calculate_bounds(struct bar_item* bar_item, uint32_t bar_height, uint32_t x, uint32_t y);
void bar_item_draw(struct bar_item* bar_item, CGContextRef context);

void bar_item_change_space(struct bar_item* bar_item, uint64_t dsid, uint32_t adid);

void bar_item_serialize(struct bar_item* bar_item, FILE* rsp);

void bar_item_parse_set_message(struct bar_item* bar_item, char* message, FILE* rsp);
void bar_item_parse_subscribe_message(struct bar_item* bar_item, char* message, FILE* rsp);
