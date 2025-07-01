default:
    @just config debug
    @echo
    @just build

[no-exit-message]
config mode:
    @xmake config --clean --mode={{mode}}

[no-exit-message]
build:
    @xmake build

[no-exit-message]
run:
    @xmake run --workdir=.

clean:
    @xmake clean

distclean:
    @rm -rf ./build
    @rm -rf ./.xmake
    @rm -rf ./.cache
