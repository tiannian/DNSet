# DNSet

> External tool to operate ipset based on domain name.

## SYNOPSIS

dnset \[OPTIONS\] \[COMMAND\]

OPTIONS := { -d/deamon | -c/config | -p/path | -l/listen }

COMMAND := { create  |destory | add | del | list | rename | help | version | daemon | reload }

dnset create \<SETNAME\>

dnset destory \<SETNAME\>

dnset rename \<SETNAME\>

dnset list \<SETNAME\>

dnset add \<SETNAME\> \<VALUE\>

dnset del \<SETNAME\> \<VALUE\>

dnset daemon

dnset reload

dnset help

dnset version

## DESCRIPTION



## DEPENDENCE

- libipset
- libuv

## OPTIONS

### COMMANDS

### CONFIGURATION

### RPC

## SEE ALSO

- ipset

- iptables

## AUTHORS

- tiannian &lt;dtiannian@aliyun.com&gt;