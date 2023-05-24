# stochastic_exam

This is a program that can extract some memory materials from a fixed format content.


## Usage

`./main.exe --file <file_path> --type <type> [--mode <mode>]`

* `--type`: `{word | unit}`

* `--mode`: `{prev | new | prev_rand}`, default: `prev`

`domain_db_path.txt` example:

```
linux_driver,C:\Users\wsdlh\Documents\documents\Linux\linux_driver_note_qa.md,unit
english_words,xxx,word
```