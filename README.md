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

`./main --domain`

or

`./main --domain </path/to/domain_db_path.txt>`

### direct mode

`./main.exe --file <file_path> --type <type> [--mode <mode>]`

* `--type`: `{word | unit}`

* `--mode`: `{prev | new | prev_rand}`, default: `prev`

`domain_db_path.txt` example:

```
linux_driver,C:\Users\wsdlh\Documents\documents\Linux\linux_driver_note_qa.md,unit
english_words,xxx,word
```