# SDR hardware

The following SDR devices are supported
* RTL2832U
  - [rtl-sdr](http://osmocom.org/projects/sdr/wiki/rtl-sdr)
  - [rtl_tcp](http://osmocom.org/projects/sdr/wiki/rtl-sdr#rtl_tcp)
* [Airspy R2 and Airspy Mini ](http://airspy.com/)
  - Limitation: Airspy HF+ is not supported due to limited bandwidth
* [I/Q RAW file](https://www.welle.io/devices/rawfile)
* [SoapySDR](https://github.com/pothosware/SoapySDR/): All SDR-devices that are supported by SoapySDR, gr-osmosdr and uhd. These are too many devices to list them all. To see if your SDR is supported, have a look at the lists at [SoapySDR](https://github.com/pothosware/SoapySDR/wiki) and [SoapyOsmo](https://github.com/pothosware/SoapyOsmo/wiki).
    * Devices supported by gr-osmosdr are supported via [SoapyOsmo](https://github.com/pothosware/SoapyOsmo/wiki)
    * Devices supported by uhd are supported via [SoapyUHD](https://github.com/pothosware/SoapyUHD/wiki)
    * Notes
      - LimeSDR: Connect the antenna to the RX1_W port and configured SoapySDR antenna option to `LNAW`. `SoapySDRUtil --probe=driver=lime` may show other possible options.
      - USRP: Configured SoapySDR driver arguments option to `driver=uhd`. Configure also antenna and clock source option. To list possible values for antenna and clock source use the command `SoapySDRUtil --probe=driver=uhd`.
      - One limitation is of course that the SDR devices must be tunable to the DAB+ frequencies.
