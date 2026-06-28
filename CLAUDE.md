# CLAUDE.md

Claude Code向けのプロジェクト固有の指示。

## プロジェクト概要

QMK/ZMKキーボードのキーマップを管理するリポジトリ。QMKとZMKの混在を許容する。
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

## Rainy75（ZMK）の編集・ビルド・書き込み

Rainy75 は QMK ではなく **ZMK**（純正が Evision/Telink の独自ファーム）。他ボードと手順が違う。

- **keymap の正本**: `keyboards/wuque_studio/rainy75/zmk/rainy75.keymap`
- **ファームのビルド/書き込み**: 別クローン `~/repos/github.com/scholzri/rainy75-zmk`
  （fork: `jaxx2104/rainy75-zmk`）で行い、その `zmk/boards/rainy75/rainy75.keymap` を
  qmk-keymaps 側と**バイト一致**で同期する（両方に同じ変更を当てる）。

### ⚠️ ブランチ（最重要）

ビルド/書き込みは必ず **`main`** で行う（`main` = 個人最終 keymap = qmk-keymaps のコピー）。
クローンは upstream PR 用の **`fix/buildable`**（原状の旧 keymap）に置かれていることがあり、
そのままビルドすると**間違ったファーム**が出る → 先に `git checkout main`。
個人 keymap 変更は `main`（＋qmk-keymaps）のみ。**`fix/buildable` には触れない**。

### ビルド → 検証 → 書き込み

```bash
cd ~/repos/github.com/scholzri/rainy75-zmk && git checkout main
export PATH="$(pwd)/toolchain/protoc/bin:$PATH" && ./build.sh -pa
# 焼く前に build/zephyr/zephyr.dts を検証（keycode = 0x07<<16|usage 例: LCTRL=0x700e0, CapsLock=0x70039）
python3 reverse/tools/restore_original.py --yes --no-verify --port /dev/ttyACM0 build/combined.bin
```

- ZMK 稼働中の更新なので bridge 不要。verify は usbipd 経由で必ずタイムアウト → **`--no-verify` 必須**。
- usbipd attach が `Device in error state`／記述子失敗ゴースト → **USB 抜き差し（別ポート）**で解消
  （初回や別ポートでは Windows 管理者 `usbipd bind` が一度要ることあり）。
- 完了後、qmk-keymaps を commit／クローン `main` を commit & push（fork）して両者を同期。

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
