# qmk-keymaps

Personal QMK/VIA keyboard keymaps.

## Keyboards

| Keyboard | Layout | Type |
|----------|--------|------|
| KBDfans KBD67 MkII RGB | 65% ANSI | QMK |
| KBDfans DZ60RGB v2 | 60% ANSI (arrow) | QMK |
| NovelKeys NK65 Entry Edition | 65% ANSI | QMK |
| RAMA WORKS KARA | 60% HHKB | QMK |
| Wuque Studio Rainy75 | 75% | VIA |

## Directory Structure

```
keyboards/
└── <vendor>/
    └── <keyboard>/
        ├── keymaps/jaxx/    # QMK keymap
        │   ├── keymap.c
        │   ├── config.h
        │   └── rules.mk
        └── via/             # VIA layout
            └── *.layout.json
```

## Features

- Japanese input switching (Eisu/Kana) with tap/hold
  - Tap: Input mode switch
  - Hold: Modifier key (GUI/Alt)
- RGB control in FN layer
- HJKL arrow keys (HHKB layout)

## Usage

### QMK

```bash
# Copy keymap to qmk_firmware
cp -r keyboards/<vendor>/<keyboard>/keymaps/jaxx \
  ~/qmk_firmware/keyboards/<vendor>/<keyboard>/keymaps/

# Build firmware
qmk compile -kb <vendor>/<keyboard> -km jaxx
```

### VIA

1. Open [VIA](https://usevia.app/)
2. Load layout JSON from `keyboards/<vendor>/<keyboard>/via/`
