#!/bin/bash

# サブモジュールのディレクトリを取得
SUBMODULE_PATHS=$(git config --file .gitmodules --get-regexp path | awk '{print $2}')

# 各サブモジュールに移動し、更新を行う
for SUBMODULE in $SUBMODULE_PATHS; do
    echo "Updating submodule: $SUBMODULE"
    
    # サブモジュールのブランチを取得（ブランチが指定されていない場合はmasterをデフォルトとする）
    BRANCH=$(git config --file .gitmodules --get "submodule.$SUBMODULE.branch")
    if [ -z "$BRANCH" ]; then
        BRANCH="master"
    fi

    # サブモジュールのディレクトリに移動
    cd $SUBMODULE
    
    # ブランチをチェックアウトし、最新の変更を取得
    git checkout $BRANCH
    git pull origin $BRANCH
    
    # メインのディレクトリに戻る
    cd -
done

echo "All submodules updated."
