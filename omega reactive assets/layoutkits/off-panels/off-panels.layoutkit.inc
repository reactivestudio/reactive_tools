name = Off Panels
description = A layout demonstrating the off canvas responsive panels.
preview = preview.png
template = {{ LAYOUT SANITIZED }}-layout

; Regions
regions[branding]       = Branding
regions[header]         = Header
regions[navigation]     = Navigation bar
regions[highlighted]    = Highlighted
regions[help]           = Help
regions[content]        = Content
regions[footer]         = Footer

; Stylesheets
stylesheets[all][] = css/layouts/{{ LAYOUT SANITIZED }}/{{ LAYOUT SANITIZED }}.layout.css
stylesheets[all][] = css/layouts/{{ LAYOUT SANITIZED }}/{{ LAYOUT SANITIZED }}.layout.no-query.css
stylesheets[all][] = libraries/sidy.js/dist/sidy.css

; Javascript
scripts[] = libraries/sidy.js/dist/sidy.js
scripts[] = js/layouts/{{ LAYOUT SANITIZED }}/{{ LAYOUT SANITIZED }}.js
