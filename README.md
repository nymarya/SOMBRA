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

If you want to draw a polygon, you must specify the `line` to the `type` argument and the keys `points` that receives the pairs with points that represent a line. For example, the input above draws 4 lines: from <10,10> to <10,200>, from <10,200> to <100, 200>, and so on.

```json
{
    "type": "polygon",
    "points": [
        [10,10],[10,200],
        [10,200],[100,200],
        [200,10],[100,200],
        [10,10], [200, 10]
    ]
}
```

### Circle

The circle structure requires the keys `centre` that receives a array with the two coordinates of the central point, and `radius`.

```json
{
    "type":"circle",
    "center": [700,150],
    "radius":150
}
```

### Arc

The `arc` type expects the same arguments as `circle`, plus the information about the angles where the arc begin and end (`start_angle` and `end_angle`, respectively)

```json
{
    "type": "arc",
    "radius": 100,
    "center": [
        500,
        500
    ],
    "color": "0,0,0",
    "start_angle": 180,
    "end_angle": 0
}
```

### Groups

You may group several types of graphic in one objec using the type `group` simply by passing all the objects at the `objects`argument.

```json
{
    "type":"group",
    "color":"255,255,255",
    "shapes":[
        {
            "type":"polygon",
            "points":[
                [800,100],[700,10],
                [800, 100],[800, 200],
                [600,200] , [800, 200],
                [600, 100], [600,200],
                [600, 100], [700, 10]
            ]
        },
        {
            "type":"circle",
            "center": [700,150],
            "radius":150
        }
    ]
}
```
