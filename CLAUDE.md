# CLAUDE.md

Claude Code向けのプロジェクト固有の指示。

## プロジェクト概要

QMK/VIA/ZMKキーボードのキーマップを管理するリポジトリ。QMKとZMKの混在を許容する。
Rainy75のみZMK（純正ファームがQMKベースでないため）。ファーム本体・ビルド・書き込みは
fork [jaxx2104/rainy75-zmk](https://github.com/jaxx2104/rainy75-zmk)、このリポジトリでは
keymap（`keyboards/wuque_studio/rainy75/zmk/rainy75.keymap`）を管理する。

## ディレクトリ構造

```
keyboards/<vendor>/<keyboard>/
├── keymaps/jaxx/    # QMKキーマップ
│   ├── keymap.c     # キーマップ定義
│   ├── config.h     # 設定（TAPPING_TERM等）
│   └── rules.mk     # ビルドオプション
├── via/             # VIA設定
│   └── *.layout.json
└── zmk/             # ZMKキーマップ（Rainy75。純正がQMK非対応のため）
    └── rainy75.keymap
```

## キーマップの共通仕様

### カスタムキーコード

- `CK_EISU`: タップで英数(KC_LNG2)、ホールドでGUI
- `CK_KANA`: タップでかな(KC_LNG1)、ホールドでAlt

ZMK（Rainy75）での等価表現:

- `CK_EISU` → `&mt LGUI LANG2`（スペース左）
- `CK_KANA` → `&mt RALT LANG1`（スペース右）

### レイヤー構成

- `_BASE`: 通常レイヤー
- `_FN`: ファンクションレイヤー（F1-F12、RGB制御、メディアキー）

### config.h 標準設定

```c
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
```

## 新しいキーボードの追加手順

1. QMK公式のディレクトリ構造に従ってベンダー名/キーボード名でディレクトリ作成
2. レイアウトマクロはキーボードに対応したものを使用（例: `LAYOUT_65_ansi`, `LAYOUT_60_hhkb`）
3. 既存のキーマップをベースにキー数を調整
4. 矢印キーの有無でFNレイヤーのHJKL設定を調整

## レイアウト対応表

| レイアウト | マクロ | 備考 |
|-----------|--------|------|
| 65% ANSI | `LAYOUT_65_ansi` | KBD67, NK65 |
| 65% ANSI blocker | `LAYOUT_65_ansi_blocker` | ブロッカー付き |
| 60% ANSI arrow | `LAYOUT_60_ansi_arrow` | 矢印キー付き60% |
| 60% HHKB | `LAYOUT_60_hhkb` | HHKB配列 |
