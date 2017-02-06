#!/bin/bash

for FILE in $(find _build/locale/ -name '*.pot'); do

    NAME=$(basename -s.pot $FILE)
    SLUG=docs-v7.${NAME}

    if grep -q -F "[${SLUG}]" .tx/config; then
        echo "Skip existing slug ${SLUG}"
        continue
    fi

    cat <<EOF >> .tx/config

[${SLUG}]
file_filter = ./locale/<lang>/LC_MESSAGES/${NAME}.po
source_file = ${FILE}
source_lang = en
type = PO

EOF
done
