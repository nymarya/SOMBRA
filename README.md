# SOMBRA
Simple Objects Minimal Bidimensional RAsterizer
 
## About

## How to use

|  Command           | Description  |
| :-----| :-------------|
| ```$ make``` | Compile |
| ```$ ./canvas.out``` | Run | 



## Usage

In order to describe a scene, specify the
filename where the image will be saved inside the `gallery` folder, as well as the objects, and the scene's width and height. 

You can choose a global color for the parameters `fill` and stroke(`color`) or define it inside the graphic object. The color is represented by a string with the format `red,green,blue`.

```json
{
	"scene": {
		"name": "canvas",
		"filename": "image",
		"width": 1000,
		"height": 1000,
		"background": "255,255,255",
		"fill":"0,255,0",
                "objects": [...]
    }
```

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

If you want to draw a polygon, you must specify the `line` to the `type` argument and the keys `points` that receives the pairs of points that represent a line. For example, the input bellow draws 4 lines: from <10,10> to <10,200>, from <10,200> to <100, 200>, and so on.

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

The circle structure requires the keys `center` that receives an array with the two coordinates of the central point, and `radius`.

```json
{
    "type":"circle",
    "center": [700,150],
    "radius":150
}
```

### Arc

The `arc` type expects the same arguments as `circle`, plus the information about the angles where the arc begins and ends (`start_angle` and `end_angle`, respectively)

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

You may group several types of graphics in one objects using the type `group` simply by passing all the objects at the `shapes` argument.

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
