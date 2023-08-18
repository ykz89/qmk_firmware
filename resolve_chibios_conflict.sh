#!/bin/bash

# サブモジュールディレクトリへ移動
cd lib/chibios

# 変更を新しいブランチにコミットしてバックアップ
git checkout -b backup_changes
git add .
git commit -m "Backup local changes"

# サブモジュールをリモートリポジトリの最新の状態にリセット
git checkout master
git fetch origin
git reset --hard origin/master

# サブモジュールを再度更新
git pull origin master

# メインのリポジトリへ移動して、サブモジュールの変更をコミット
cd ../..
git add lib/chibios
git commit -m "Updated ChibiOS submodule"

echo "ChibiOSの競合が解消されました。"
