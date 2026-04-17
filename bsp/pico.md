# RP2040

![](fig/pico-pinout.svg)

## Micropython

You can tell indirectly by looking to see if network functionality is included in your particular firmware:

    import network
    if hasattr(network, "WLAN"):
        # the board has WLAN capabilities

## References

- Official [page](https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html#layouts)