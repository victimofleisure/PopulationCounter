# PopulationCounter

Displays a dynamically updated estimate of the global human population

The program is a simple dialog app, and can go full screen via F11. 
The font automatically resizes to fit the window. The estimate is 
based on exponential growth from an initial population at a fixed 
annual growth rate. The default values for initial population, 
census date, and growth rate are taken from worldometers.info. 
The actual growth rate varies and may cause the counter to become 
less accurate over the years. To address this, override the default 
values via the command line. The following command line parameters 
are supported:

~~~
/n N    N is the initial population count (no commas!)
/d D    D is the census date in MM/DD/YYYY format only
/g G    G is the annual growth rate (not a percentage!)
/f      launch in full screen mode
~~~

Sample command line:
PopulationCounter /n 7714576923 /d 7/1/2019 /g 0.0107

The date format is fixed and doesn't vary by region. The above growth 
rate is equivalent to 1.07 percent. The parameter names aren't case 
sensitive, and they can be prefixed with a hyphen instead of a slash.

Features:
* Full screen mode, via F11 or the dialog's system menu
* Font automatically resizes to fit the window
* Region-appropriate thousands separators
* Initial population, census date and annual growth rate can be 
  overriden via command line for improved accuracy as the growth 
  rate (hopefully) continues to decrease

Copyleft 2019 Chris Korda
This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2 of the License, or any later version.
