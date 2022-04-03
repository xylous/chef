# chef v0.1.0

`chef` is a chess engine.

It's still in its development phase, and not usable!

For a detailed history of the project, check [the Changelog](./Changelog.md)

## Getting started

### Reguirements

Build-time dependencies:
- (GNU) make
- a C compiler

### Installation

Clone this repository locally and build using `make`:

```
git clone https://github.com/xylous/chef chef
cd chef
make
```

## Roadmap

- [x] board representation, using bitboards
- [x] printing a chess board
- [ ] REPL
    - [ ] be able to move anywhere without checking for valid moves
    - [ ] check if the move performed is legal
- [ ] move generation
- [ ] ~~CLI interface~~
- [ ] interactive interface (stdin)
- [ ] opening book
- [ ] 500  ELO
- [ ] 1000 ELO

## Contributing

Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[GPLv3](./LICENSE)
