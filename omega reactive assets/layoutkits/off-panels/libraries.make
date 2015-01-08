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
; Normally, this would be 'sites/all/themes/{{ THEME }}/layouts/{{ LAYOUT SANITIZED }}'.
;
; $ cd ./
;
; Now you can invoke 'drush make' using the following command:
;
; $ drush make sites/all/themes/{{ THEME }}/layouts/{{ LAYOUT SANITIZED }}/libraries.make --no-core --contrib-destination=sites/all/themes/{{ THEME }}
;
; ##############################################################################

core = 7.x
api = 2

libraries[Sidy][download][type] = "git"
libraries[Sidy][download][url] = "git://github.com/reactivestudio/Sidy.js.git"
