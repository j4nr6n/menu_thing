#include <U8g2lib.h>
#include "Memory.h"

#define ROT_BTN 2
#define ROT_CLK 3
#define ROT_DAT 4

#define MENU_SCR -1

#define SEL_MENU_ITEM_MEM_ADDR 1

#define OUT_0 6
#define OUT_1 7
#define OUT_2 8

#define OUT_0_MEM_ADDR 10
#define OUT_1_MEM_ADDR 11
#define OUT_2_MEM_ADDR 12

// 'item_sel_background', 128x21px
const unsigned char bitmap_item_sel_background[] PROGMEM = {
  0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06,
  0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03,
  0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01
};

// 'scroll_bar', 8x64px
const unsigned char bitmap_scroll_bar[] PROGMEM = {
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40,
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40,
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40,
  0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00
};

// 'icon_next', 16x16px
const unsigned char bitmap_icon_next[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x14, 0x28, 0x24, 0x24, 0x48, 0x12,
  0x90, 0x09, 0x20, 0x04, 0x40, 0x02, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'icon_prev', 16x16px
const unsigned char bitmap_icon_prev[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x40, 0x02, 0x20, 0x04, 0x90, 0x09,
  0x48, 0x12, 0x24, 0x24, 0x14, 0x28, 0x0c, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'icon_selected', 16x16px
const unsigned char bitmap_icon_selected[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x10, 0x08, 0xc8, 0x13, 0x24, 0x24, 0x94, 0x29, 0x54, 0x2a,
  0x54, 0x2a, 0x94, 0x29, 0x24, 0x24, 0xc8, 0x13, 0x10, 0x08, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00
};

const int NUM_ITEMS = 3;

// Array of all bitmap icons for convenience.
const unsigned char* item_icons[NUM_ITEMS] = {
  bitmap_icon_selected,
  bitmap_icon_selected,
  bitmap_icon_selected
};

const char item_titles[NUM_ITEMS][11] = {
  { "Output #00" },
  { "Output #01" },
  { "Output #02" },
};

int item_sel_prev = 0;
int item_sel_curr = 1;
int item_sel_next = 2;

volatile int rot_val = item_sel_curr;
int last_rot_val = item_sel_curr;

volatile bool btn_pressed = false;

int scroll_handle_height = 64 / NUM_ITEMS;

int current_screen = MENU_SCR;

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

Memory memory;

void setup() {
  Serial.begin(19200);

  pinMode(ROT_CLK, INPUT_PULLUP);  // TODO: No pull up on the rotary encoder?
  pinMode(ROT_DAT, INPUT_PULLUP);  // TODO: No pull up on the rotary encoder?

  pinMode(ROT_BTN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ROT_CLK), rotaryInterruptHandler, LOW);
  attachInterrupt(digitalPinToInterrupt(ROT_BTN), buttonInterruptHandler, LOW);

  // Setup the outputs
  pinMode(OUT_0, OUTPUT);
  pinMode(OUT_1, OUTPUT);
  pinMode(OUT_2, OUTPUT);

  u8g2.setBitmapMode(1);
  u8g2.begin();

  u8g2.clearDisplay();
  delay(1500);

  Serial.println("----------");
  Serial.println("Menu Thing");
  Serial.println("----------");
}

void loop() {
  digitalWrite(OUT_0, memory.read(OUT_0_MEM_ADDR));
  digitalWrite(OUT_1, memory.read(OUT_1_MEM_ADDR));
  digitalWrite(OUT_2, memory.read(OUT_2_MEM_ADDR));

  switch (current_screen) {
    case MENU_SCR:
      drawMenu();
      break;
    default:
      drawItem(current_screen);
      break;
  }
}

void drawMenu() {
  if (btn_pressed) {
    current_screen = item_sel_curr;
    memory.update(SEL_MENU_ITEM_MEM_ADDR, item_sel_curr);
    
    rot_val = memory.read(10 + item_sel_curr);

    btn_pressed = false;

    return;
  }

  if (rot_val != last_rot_val) {
    item_sel_curr = rot_val;
    if (item_sel_curr < 0) {
      rot_val = item_sel_curr = NUM_ITEMS - 1;
    }

    if (item_sel_curr >= NUM_ITEMS) {
      rot_val = item_sel_curr = 0;
    }

    item_sel_prev = item_sel_curr - 1;
    if (item_sel_prev < 0) {
      item_sel_prev = NUM_ITEMS - 1;
    }

    item_sel_next = item_sel_curr + 1;
    if (item_sel_next >= NUM_ITEMS) {
      item_sel_next = 0;
    }

    last_rot_val = rot_val;
  }

  int scroll_percentage = map(item_sel_curr, 0, NUM_ITEMS, 0, 100);

  u8g2.firstPage();
  do {
    // Prev Item
    u8g2.drawXBMP(4, 2, 16, 16, item_icons[item_sel_prev]);
    u8g2.setFont(u8g2_font_7x14_mf);
    u8g2.drawStr(26, 15, item_titles[item_sel_prev]);

    // Selected Item
    u8g2.drawXBMP(4, 24, 16, 16, item_icons[item_sel_curr]);
    u8g2.setFont(u8g2_font_7x14B_mf);
    u8g2.drawStr(26, 37, item_titles[item_sel_curr]);

    u8g2.drawXBMP(0, 22, 128, 21, bitmap_item_sel_background);

    // Next Item
    u8g2.drawXBMP(4, 46, 16, 16, item_icons[item_sel_next]);
    u8g2.setFont(u8g2_font_7x14_mf);
    u8g2.drawStr(26, 59, item_titles[item_sel_next]);

    // Scroll Bar
    u8g2.drawXBMP(120, 0, 8, 64, bitmap_scroll_bar);

    // Scroll Handle
    u8g2.drawBox(125, getScrollPixel(scroll_percentage), 3, scroll_handle_height);
  } while (u8g2.nextPage());
}

int getScrollPixel(int val) {
  return map(val, 0, 100, 0, 64);
}

void drawItem(int val) {
  if (btn_pressed) {
    memory.update(10 + val, last_rot_val);

    btn_pressed = false;

    return toMenu();
  }

  int curr_val = rot_val;

  if (rot_val != last_rot_val) {
    if (curr_val < 0) {
      rot_val = curr_val = 1;
    }

    if (curr_val > 1) {
      rot_val = curr_val = 0;
    }

    last_rot_val = rot_val;
  }

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_7x14B_mf);
    u8g2.drawStr(26, 37, "Status: ");
    u8g2.drawStr(80, 37, (curr_val == 1) ? "On" : "Off");
  } while (u8g2.nextPage());
}

void toMenu() {
  current_screen = MENU_SCR;
  rot_val = memory.read(SEL_MENU_ITEM_MEM_ADDR);
}

void rotaryInterruptHandler() {
  static unsigned long last_rot_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_rot_interrupt_time > 5) {
    if (digitalRead(ROT_DAT) == LOW) {
      --rot_val;
    } else {
      ++rot_val;
    }
  }

  last_rot_interrupt_time = interrupt_time;
}

void buttonInterruptHandler() {
  static unsigned long last_btn_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_btn_interrupt_time > 5) {
    btn_pressed = true;
  }

  last_btn_interrupt_time = interrupt_time;
}
