# GUI and command-line usage

Since welle.io is a GUI program simply start it.

#### Command-line parameters

Parameter | Description
------ | ----------
-h, --help | Show help
-v, --version | Show version
--dump-file | Records DAB frames (*.mp2) or DAB+ superframes with RS coding (*.dab). This file can be used to analyse X-PAD data with XPADxpert (https://www.basicmaster.de/xpadxpert).
--log-file | Log file name. Redirects all log output texts to a file.

#### Keyboard shortcuts & hotkeys

Keystroke | Action
------ | ----------
F1-F12, 1-9, 0, Ctrl+1-9, Ctrl+0 | Play the station no. 'x' in the stations list: <br />`1` for station no. `1`, <br />`0` for station no. `10`, <br />`Ctrl+1` for station no. `11`...
S, Media Play, Media Stop, Media Pause, Media Play/Pause | Start playback/Stop
N, Media next | play next station in list
P, Media Previous | play previous station
M, Volume Mute | mute/unmute
Ctrl+Up, Volume Up | Volume Up
Ctrl+Down, Volume Down | Volume Down

## welle-cli

If you compile welle-io with [CMake](building.md#cmake) you will also get an executable called **welle-cli** which stands for welle-io **c**ommand **l**ine **i**nterface.

#### Usage of welle-cli


Receive using RTLSDR, and play with ALSA:

    welle-cli -c channel -p programme

Read an IQ file and play with ALSA: (IQ file format is u8, unless the file ends with FORMAT.iq)

    welle-cli -f file -p programme

Use -D to dump FIC and all programmes to files:

    welle-cli -c channel -D

Use -w to enable webserver, decode a programme on demand:

    welle-cli -c channel -w port

Use -Dw to enable webserver, decode all programmes:

    welle-cli -c channel -Dw port

Use `-C 1 -w` to enable webserver, decode programmes one by one in a carousel.
Use `-C N -w` to enable webserver, decode programmes N by N in a carousel.
This is useful if your machine cannot decode all programmes simultaneously, but you still want to get an overview of the ensemble.
By default, welle-cli will switch every 10 seconds.
With the `-P` option, welle-cli will switch once DLS and a slide were decoded, staying at most for 80 seconds on a given programme.

    welle-cli -c channel -C 1 -w port
    welle-cli -c channel -PC 1 -w port

Example: `welle-cli -c 12A -C 1 -w 7979` enables the webserver on channel 12A, please then go to http://localhost:7979/ where you can observe all necessary details for every service ID in the ensemble, see the slideshows, stream the audio (by clicking on the Play-Button), check spectrum, constellation, TII information and CIR peak diagramme.

#### Streaming output options

By default, `welle-cli` will output in mp3 if in webserver mode.
With the `-O` option, you can choose between mp3 and flac (lossless) if FLAC support is enabled at build time.

#### Backend options

`-u` disable coarse corrector, for receivers who have a low frequency offset.

Use `-t [test_number]` to run a test. To understand what the tests do, please see source code.

#### Driver options

By default, `welle-cli` tries all enabled drivers in turn and uses the first device it can successfully open.

Use `-F [driver][,driver_args]` to select a specific driver and optionally pass arguments to the driver.
This allows to select the `rtl_tcp` driver (which is not auto-detected) and pass the hostname or IP address and port of the rtl_tcp server to it:

    welle-cli -c 10B -p GRRIF -F rtl_tcp,192.168.12.34:1234
    welle-cli -c 10B -p GRRIF -F rtl_tcp,my.rtl-tcp.local:9876

Right now, `rtl_tcp` is the only driver that accepts options from the command line.

**Examples**:


    welle-cli -c 10B -p GRRIF
    welle-cli -f ./ofdm.iq -p GRRIF
    welle-cli -f ./ofdm.iq -t 1
