<div class="sidy">
    <!-- Panels -->
    <?php foreach (${{ LAYOUT }}_config as $name => $o) { ?>
        <div
        <?php print (isset($o['position']))? 'data-position="'.$o['position'].'"': ''; ?>
        <?php print (isset($o['size']))? 'data-size="'.$o['size'].'"': ''; ?>
        <?php print (isset($o['fx']))? 'data-fx="'.$o['fx'].'"': ''; ?>
        class="sidy__panel" id="<?php print $name; ?>">
            <?php print render($page['panel_'.$name]); ?>
        </div>
    <?php }?>

    <!-- this is the wrapper for the content -->
    <div class="sidy__content">
        <?php include 'simple-layout.tpl.php'; ?>
    </div>
</div>
