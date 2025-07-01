default:
    @just config debug
    @echo
    @just build

[no-exit-message]
config mode:
    @xmake config --clean --mode={{mode}}

[no-exit-message]
build:
    @# echo Generating compile_commands.json ...
    @# xmake project -k compile_commands --lsp=clangd build >/dev/null
    @# echo Done
    @# echo
    @xmake build

[no-exit-message]
run: build
    @xmake run --workdir=.

clean:
    @xmake clean

distclean:
    @rm -rf ./build
    @rm -rf ./.xmake
    @rm -rf ./.cache
