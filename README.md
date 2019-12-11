# GalenaCpp

Custom programming language

## Dependencies

- [Bison](https://www.gnu.org/software/bison/)
- [Flex](https://www.gnu.org/software/flex/)
- [SFML](https://www.sfml-dev.org/tutorials/2.5/start-linux.php)

I recommend using linux or the [Windows Subsystem Linux](https://docs.microsoft.com/fr-fr/windows/wsl/install-win10) with [Xming](https://sourceforge.net/projects/xming/)

## Structure

- *build/* contains all the compiled object files
- *doc/* contains the documentation
- *spikes/* contains small scripts for testing methods or libraries
- *src/* contains all the major source files

## Building

```bash
make build
```

## Running

```bash
./program source_file.gpp
```

or

```bash
./program PGR_SOURCE=source_file.gpp
```

## Documentation

- [doc-fr](./doc/doc-fr.md)

## Examples

- [variables](./examples/variables.gpp)
- [operators](./examples/operators.gpp)
- [conditions](./examples/conditions.gpp)
- [io](./examples/io.gpp)
- [routines](./examples/routines.gpp)
- [plot](./examples/plot.gpp)

## License

MIT License

Copyright (c) 2019 ARBACHE Rémi & MIQUET Gautier

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
