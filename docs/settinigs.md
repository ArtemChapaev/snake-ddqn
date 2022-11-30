---
layout: default
title: Settings
permalink: /settings
---

# Settings

You can configure:
- map (size, solid walls, bonus apples, score display)
- type of graphics (symbolic or escape, color of bonuses)
- snake (speed, length change on a new level)
- control buttons
- create your own map (map constructor)

To do this, you must choose "Settings" in the main menu. After that, you can pick settings you need.

A general essence of changing settings is to press enter (or other if you changed "Enter key" in the "Control settings"),
to input a significant value and to confirm changes pressing "Enter key".

## Snake settings

In page "Snake settings" you can change the speed of snake and enable or disable reset length at new level.
For changing speed you can enter positive integer or positive float number. To enable reset length, you must input 1, on the contrary,
to disable, you must input 0.

## Map settings

In page "Map settings" you can change map width or map length, enable or disable solid walls, bonus apples, displaying score counter.
For changing map width or map length you can enter positive integer number. To enable other settings, you must input 1, 
on the contrary, to disable, you must input 0.

In this page also there is features of create a custom map. If you pick this item, a playing field will appear in front of you.
To move you can use arrows (or other symbols of control, if you changed them). To press "Wall key" (by default 'w'), if you 
want set the wall. To set the teleports, you must press "Teleport key" (by default 't'). If you want to back empty cell, you can press
"Empty key" (by default 'e').

For example, you can watch this gif.
<img src='https://github.com/ArtemChapaev/Snake/blob/Linux_version/docs/map_editor.gif?raw=true'/>


## Graphics settings

In page "Graphics settings" you can change the view mode or game colors. For changing view mode you can input '1', '2' or '3'.
'1' means simple symbol graphics, '2' means symbol graphics with using foreground colors, '3' means graphics with using 
background colors. For changing game colors you can enter number from 1 to 18. You can select "Possible colors", you want
to see matching numbers to colors.

## Control settings

In page "Control settings" you can change the control symbols. Changing of these settings is similar other settings. You can
enter  any character of keyboard.

## Presets
There is feature of using presets. You can store 3 presets. To pick action with preset, you must press "Enter key" (by default enter).


## License
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)