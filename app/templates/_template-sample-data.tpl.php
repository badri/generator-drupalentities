<?php

/**
 * @file
 * Example tpl file for theming a single <%= moduleName %>-specific theme
 *
 * Available variables:
 * - $status: The variable to theme (while only show if you tick status)
 *
 * Helper variables:
 * - $<%= moduleName %>: The <%= className %> object this status is derived from
 */
?>

<div class="<%= moduleName %>-status">
  <?php print '<strong><%= className %> Sample Data:</strong> ' . $<%= moduleName %>_sample_data = ($<%= moduleName %>_sample_data) ? 'Switch On' : 'Switch Off' ?>
</div>
