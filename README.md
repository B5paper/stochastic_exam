# stochastic_exam

This is a program that can extract some memory materials from a fixed format content.


## Usage

### domain mode

create a file named `domain_db_path.txt` at the binary executable folder, and the file content is used to specify the domain info database.

Example:

`domain_db_path.txt`:

```
/home/hlc/Documents/documents/domain_db.txt
```

The program will then read the content of `domain_db.txt` to locate every qa (Question and Answer) file.

The format of `domain_db.txt` would like to be:

```
opengl,GPU/opengl_note_qa.md,unit
opencl,High Performance Computing/opencl_note_qa,unit
english_words.md,Language/english_words.md,word
```

Obviously, there are two types of qa: `unit` and `word`. Currently the type `word` has not been implemented.

Usage:

* `./main --mode domain --meta_info_path <file_path>`

    Run command `./main` without arguments will defaultly use `domain` mode and search meta info file `meta_info.txt` at the same directory containing `main`.

* `./main --mode list --meta_info_path <file_path>`

    list all entities of a note file.

### direct mode

`./main.exe --file <file_path> --type <type> [--mode <mode>]`

* `--type`: `{word | unit}`

* `--mode`: `{prev | new | prev_rand | seq}`, default: `seq`

    If you choose `seq`, the test unit will be displayed one by one in order.

`domain_db_path.txt` example:

```
linux_driver,C:\Users\wsdlh\Documents\documents\Linux\linux_driver_note_qa.md,unit
english_words,xxx,word
```