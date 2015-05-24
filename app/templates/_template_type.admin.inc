<?php

/**
 * @file
 * <%= className %> type editing UI.
 */

/**
 * UI controller.
 */
class <%= className %>TypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
		$items[$this->path]['description'] = 'Manage <%= entityLabel %> entity types, including adding
		and removing fields and the display of fields.';
    return $items;
  }
}

/**
 * Generates the <%= moduleName %> type editing form.
 */
function <%= moduleName %>_type_form($form, &$form_state, $<%= moduleName %>_type, $op = 'edit') {

  if ($op == 'clone') {
    $<%= moduleName %>_type->label .= ' (cloned)';
    $<%= moduleName %>_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $<%= moduleName %>_type->label,
    '#description' => t('The human-readable name of this <%= moduleName %> type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($<%= moduleName %>_type->type) ? $<%= moduleName %>_type->type : '',
    '#maxlength' => 32,
//    '#disabled' => $<%= moduleName %>_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => '<%= moduleName %>_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this <%= moduleName %> type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['data']['#tree'] = TRUE;
  $form['data']['sample_data'] = array(
    '#type' => 'checkbox',
    '#title' => t('An interesting <%= moduleName %> switch'),
    '#default_value' => !empty($<%= moduleName %>_type->data['sample_data']),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save <%= moduleName %> type'),
    '#weight' => 40,
  );

  //Locking not supported yet
  /*if (!$<%= moduleName %>_type->isLocked() && $op != 'add') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete <%= moduleName %> type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('<%= moduleName %>_type_form_submit_delete')
    );
  }*/
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function <%= moduleName %>_type_form_submit(&$form, &$form_state) {
  $<%= moduleName %>_type = entity_ui_form_submit_build_entity($form, $form_state);
  $<%= moduleName %>_type->save();
  $form_state['redirect'] = 'admin/structure/<%= moduleName %>_types';
}

/**
 * Form API submit callback for the delete button.
 */
function <%= moduleName %>_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/<%= moduleName %>_types/manage/' . $form_state['<%= moduleName %>_type']->type . '/delete';
}
