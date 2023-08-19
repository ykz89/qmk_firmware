#!/bin/bash

SUBMODULES=(
    arm_atsam
    chibios
    chibios-contrib
    fnv
    googletest
    lib8tion
    lufa
    lvgl
    pico-sdk
    printf
    python
    usbhost
    vusb
)

for submodule in "${SUBMODULES[@]}"; do
    echo "=== 処理中: $submodule ==="

    # サブモジュール内の変更を確認
    echo "$submodule の変更状態を確認します:"
    (cd "lib/$submodule" && git status)

    # サブモジュールの変更を破棄
    echo "$submodule 内の変更を破棄します:"
    (cd "lib/$submodule" && git reset --hard)

    # サブモジュールを最新の状態に更新
    echo "$submodule を最新の状態に更新します:"
    git submodule update --init "lib/$submodule"

    echo "=== $submodule の処理が完了しました ==="
    echo
done

# サブモジュールの状態を再確認
echo "全サブモジュールの状態を再確認します:"
git status

echo "処理が完了しました。"
