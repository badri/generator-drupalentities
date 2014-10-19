<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying edit links
 * as fields
 */


class <%= moduleName %>_handler_edit_link_field extends <%= moduleName %>_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }


  function render($values) {
    $type = $values->{$this->aliases['type']};

    //Creating a dummy <%= moduleName %> to check access against
    $dummy_<%= moduleName %> = (object) array('type' => $type);
    if (!<%= moduleName %>_access('edit', $dummy_<%= moduleName %>)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    $<%= entityId %> = $values->{$this->aliases['<%= entityId %>']};

    return l($text, 'admin/content/<%= moduleName %>s/<%= moduleName %>/' . $<%= entityId %> . '/edit');
  }
}
