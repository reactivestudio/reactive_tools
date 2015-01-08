; ##############################################################################
;
; This is a Drush make file that will automatically download the front-end
; libraries used by layouts in {{ THEME }} Omega theme.
; Alternatively, you can use Bower (http://bower.io) to
; accomplish this.
;
; Running Drush make in your  will cause the libraries to be downloaded
; into your theme. If you want to download them into Omega directly to make them
; available to all of your sub-themes (if you have multiple) then you should
; instead run omega.make from the Omega theme directory.
;
; To run this file with 'drush make' you first have to navigate into your theme.
; Normally, this would be 'sites/all/themes/{{ THEME }}/layouts/{{ LAYOUT }}'.
;
; $ cd sites/all/themes/{{ THEME }}/layouts/{{ LAYOUT }}
;
; Now you can invoke 'drush make' using the following command:
;
; $ drush make libraries.make --no-core --contrib-destination=.
;
; ##############################################################################

core = 7.x
api = 2

; libraries[sidebarEffects][download][type] = "file"
; libraries[sidebarEffects][download][url] = "https://github.com/codrops/SidebarTransitions/archive/master.zip"
