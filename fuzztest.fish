#!/usr/bin/env fish
argparse 'n/num=' -- $argv

function gen_rand
  echo (openssl rand -base64 12)
end

for i in (seq 1 $_flag_n)
  bash -c "./main ./testdata/test_table.md $(gen_rand) $(gen_rand)"
end

