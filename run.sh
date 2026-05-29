#!/usr/bin/env bash
set -e
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
APP="$PROJECT_ROOT/build/imperative_clustering"
DATA_DIR="$PROJECT_ROOT/data"
FILE="$1"
if [[ ! "$FILE" == /* && ! "$FILE" == ./* && ! "$FILE" == ../* ]]; then
  if [[ -f "$DATA_DIR/$FILE" ]]; then
    FILE="$DATA_DIR/$FILE"
  else
    echo "Файл не найден: $DATA_DIR/$FILE"
    exit 1
  fi
elif [[ ! -f "$FILE" ]]; then
  echo "Файл не найден: $FILE"
  exit 1
fi
if [[ $# -ge 6 ]]; then
  echo -e "$2\n$3\n$4\n$5\n$6" | "$APP" "$FILE"
else
  "$APP" "$FILE"
fi