# Convert JPG to PPM

## Dependencies

* ImageMagick

## Installation

```bash
$ sudo apt install imagemagick
```


## Conversion

### Convert to PPM P3 (ASCII)

```bash
$ convert -compress none a.jpg b.ppm
```

### Convert to PPM P6 (Binary)

```bash
$ convert a.jpg c.ppm
```

