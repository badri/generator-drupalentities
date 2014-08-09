<?php

/**
 * This field handler aggregates operations that can be done on a <%= moduleName %>
 * under a single field providing a more flexible way to present them in a view
 */
class <%= moduleName %>_handler_<%= moduleName %>_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['<%= moduleName %>_id'] = '<%= moduleName %>_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('<%= moduleName %>', 'admin/content/<%= moduleName %>s/<%= moduleName %>', array($this->get_value($values, '<%= moduleName %>_id')));

    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
