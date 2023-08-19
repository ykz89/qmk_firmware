#!/bin/bash

# QMKのルートディレクトリからこのスクリプトを実行することを想定しています。
# 探す関数のリスト
functions=("adc_init" "adc_gpio_init" "adc_select_input" "adc_read" "sleep_ms")

# Pico SDKのソースディレクトリへのパス
pico_sdk_dir="./lib/pico-sdk"

echo "Searching for functions..."

# 各関数のためのループ
for func in "${functions[@]}"; do
    echo "Searching for $func..."
    
    # grepコマンドを使用して関数の定義を検索します
    result=$(grep -r "$func(" $pico_sdk_dir)
    
    if [ -n "$result" ]; then
        echo "$func found in:"
        
        # マッチしたファイルのリストを表示
        echo "$result" | cut -d ':' -f 1 | uniq
    else
        echo "$func not found."
    fi

    echo "------------------------------------"
done
