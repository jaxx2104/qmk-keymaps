# Rainy 75 (ZMK)

The Wuque Studio / Wobkey Rainy 75 Pro runs **ZMK**, not QMK — its stock firmware is a
proprietary Evision/Telink (TLSR9511 / B91, RISC-V) platform, not QMK-based, so there is
no `keymap.c`. The keymap lives in [`rainy75.keymap`](rainy75.keymap) (a ZMK devicetree
keymap).

- **Full firmware, build and flashing:** [jaxx2104/rainy75-zmk](https://github.com/jaxx2104/rainy75-zmk)
  — a fork of [scholzri/rainy75-zmk](https://github.com/scholzri/rainy75-zmk) (an open ZMK
  port). This file is the source of truth for the keymap; it is built from that repo at
  `zmk/boards/rainy75/rainy75.keymap`.
- **Layout: ANSI.** The physical wide Enter is wired to matrix `RC(3,13)`, which the
  upstream ISO `matrix-transform` skips — so this keymap also depends on the `RC(3,13)`
  addition in the fork's `rainy75.dts`. (Upstream's `#ifdef CONFIG_RAINY75_ANSI` never
  activates — the keymap overlay is preprocessed before Kconfig — so the ANSI block is
  hardcoded here. Details: scholzri/rainy75-zmk#1.)

## Japanese input (the ZMK equivalent of QMK's `CK_EISU` / `CK_KANA`)

| QMK (other boards) | ZMK (here) | Position |
|---|---|---|
| `CK_EISU` — tap 英数 (KC_LNG2), hold GUI | `&mt LGUI LANG2` | left of Space |
| `CK_KANA` — tap かな (KC_LNG1), hold Alt | `&mt RALT LANG1` | right of Space |

## Layers

- **Layer 0** — base.
- **Layer 1 (`Fn`)** — media keys (Fn+F5–F12), Bluetooth profile select (Fn+F1/F2/F3),
  USB/BLE output toggle (Fn+F4), RGB controls, and ZMK Studio unlock (Fn+Esc).

## `../via/`

[`../via/rainy_75.layout.json`](../via/rainy_75.layout.json) is the original stock VIA
layout. It is kept as the authoritative **matrix reference** — it is how the ANSI Enter
and bottom-row matrix positions were pinned down — but VIA is no longer used for this
board.
