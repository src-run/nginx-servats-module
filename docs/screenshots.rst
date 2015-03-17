###########
Screenshots
###########

While the *Scribe / Nginx Servats Module* can be configured with user-supplied
CSS and JavaScript includes, its default configuration includes a comprehensive
theme that utilizes the following open-source projects.

- `Bootstrap (v3.3.4) <http://getbootstrap.com/>`_
- `jQuery (v2.1.3) <http://jquery.com/>`_
- `Chart.js (v1.0.2) <http://www.chartjs.org/>`_
- `Stupid Table (master) <https://github.com/joequery/Stupid-Table-Plugin>`_
- `Font Awesome (v4.3.0) <http://fortawesome.github.io/Font-Awesome/>`_
- `Google Fonts <http://www.google.com/fonts/>`_

Main Window
===========

The main window is a responsive Bootstrap layout that scales effectively to
varying device screen widths. The header displays the machine *host name*, *server
version*, as well as *module version*. The footer displays the time the page was
rendered.

.. figure:: /images/servats-overview-01.png
   :scale: 100 %
   :align: center
   :alt: The main window, showing the header, footer, and all available sections.

.. figure:: /images/servats-overview-02.png
   :scale: 100 %
   :align: center
   :alt: The main window, focused on content sections.

Workers
=======

The "Workers" section features tool-tips that describes the *Mode* icon with
basic phrases such as "Waiting for response," "Sending reply," as well as other
possible states.

.. figure:: /images/servats-workers-01.png
   :scale: 75 %
   :align: center
   :alt: Worker listings with tool-tip describing the "Mode" as "Waiting for response".

.. figure:: /images/servats-workers-02.png
   :scale: 75 %
   :align: center
   :alt: Worker listings with tool-tip describing the "Mode" as "Sending reply".

Connections
===========

The "Connections" section lists information pertaining to connections, including
their related *worker*, *requests count*, *mode*, *request size (bytes)*, *client
IP*, *server name*, *GZip compression*, *age*, *request code*, *time*, *upstream
(proxy) time*, and *URI*. Both the *Mode* and *Code* feature tool-tips that
describe the state.

.. figure:: /images/servats-connections-01.png
   :scale: 100 %
   :align: center
   :alt: Connection listings with tool-tip describing the "Mode" as "Innactive connection".

.. figure:: /images/servats-connections-02.png
   :scale: 100 %
   :align: center
   :alt: Connection listings with tool-tip describing the "Code" as "200: OK".

.. figure:: /images/servats-connections-03.png
   :scale: 100 %
   :align: center
   :alt: Connection listings with tool-tip describing the "Code" as "404: Not Found".
