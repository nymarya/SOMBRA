# SOMBRA
Simple Objects Minimal Bidimensional RAsterizer
 
## About

## How to use

## Usage

Palette, scene, canvas

### Line

In order to define a line, you must specify the `line` to the `type` argument and the keys `p1`, `p2`, besides the other elements available to all the graphic types, except for  `fill`.

```json
{
    "type": "line",
    "p1": [10,10],
    "p2": [10,200],
    "color":"black"
}
```
### Polygon

If you want to draw a polygon, you must specify the `line` to the `type` argument and the keys `points` that receives the 


- [ ] Linha 

    - [x] Segmento de linha
    - [x] Polilinha
- [x] Círculo 
- [x] Semi-círculo
- [ ] Elipse [opcional]
- [ ] Preenchimento
    - [ ] Scan-line approach
    - [x] Fill
- [x] Antialiasing
- [ ] Paleta de cores
