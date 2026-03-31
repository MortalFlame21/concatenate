# Concatenate

Print and join file contents from a list of files. A UNIX `cat` subset clone.

## Requirements

Although simple, this program needs a C++20 compliant compiler and GNU make 4.x+ to compile.

## Usage

```shell
make

./build/concatenate <OPTIONS> <FILE>
```

`<OPTIONS>` are used to select how characters and lines are printed.

`<FILE>` is a list of valid file paths. The paths contents will thus be printed in respective order. A path of `-` indicates standard input.

To mark end of `<OPTIONS>`, `--`, indicates that subsequent arguments will be treated as `<FILE>`.

```shell
<OPTIONS>
    -a, --all
        Enable all options, similar to -let
    -l, --lines
        Print line number prior to line.
    -e, --ends
        Convert newline characters to "\\n".
    -t, --tabs
        Convert tab characters to "\\t".
```

### Example

Please see `eg/` for example test files.

```shell
./build/concatenate test.txt -
testing
hellohello
```
