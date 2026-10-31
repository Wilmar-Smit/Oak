#!/usr/bin/env bash

if [ -n "$GLIBC_LOCALES_PATH" ]; then
  export LOCALE_ARCHIVE="$GLIBC_LOCALES_PATH/lib/locale/locale-archive"
  export LC_ALL="en_US.UTF-8"
fi

if [ -z "$IN_NIX_FISH" ]; then
  export IN_NIX_FISH=1

  exec fish -C '
    if functions -q fish_prompt
      functions -c fish_prompt _old_fish_prompt
      function fish_prompt
        set_color -o 33af85
        echo -n "🌳(nix-oak) "
        set_color normal
        _old_fish_prompt
      end
    else
      function fish_prompt
        set_color -o 33af85
        echo -n "🌳(nix-oak) "
        set_color blue
        echo -n (prompt_pwd)
        set_color brgreen
        echo -n " > "
        set_color normal
      end
    end
  '
fi