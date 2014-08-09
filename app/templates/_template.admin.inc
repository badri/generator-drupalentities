<?php

/**
 * @file
 * <%= className %> editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

/**
 * UI controller.
 */
class <%= className %>UIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {

    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => '<%= className %>s',
      'description' => 'Add edit and update <%= moduleName %>s.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );

    // Change the overview menu type for the list of <%= moduleName %>s.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a <%= moduleName %>',
      'description' => 'Add a new <%= moduleName %>',
      'page callback'  => '<%= moduleName %>_add_page',
      'access callback'  => '<%= moduleName %>_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => '<%= moduleName %>.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );

    // Add menu items to add each different type of entity.
    foreach (<%= moduleName %>_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => '<%= moduleName %>_form_wrapper',
        'page arguments' => array(<%= moduleName %>_create(array('type' => $type->type))),
        'access callback' => '<%= moduleName %>_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => '<%= moduleName %>.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing <%= moduleName %> entities
    $items[$this->path . '/<%= moduleName %>/' . $wildcard] = array(
      'page callback' => '<%= moduleName %>_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => '<%= moduleName %>_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => '<%= moduleName %>.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/<%= url %>/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );

    $items[$this->path . '/<%= url %>/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => '<%= moduleName %>_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => '<%= moduleName %>_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => '<%= moduleName %>.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );

    // Menu item for viewing <%= moduleName %>s
    $items['<%= moduleName %>/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => '<%= moduleName %>_page_title',
      'title arguments' => array(1),
      'page callback' => '<%= moduleName %>_page_view',
      'page arguments' => array(1),
      'access callback' => '<%= moduleName %>_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }


  /**
   * Create the markup for the add <%= className %> Entities page within the class
   * so it can easily be extended/overriden.
   */
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }

    return theme('<%= moduleName %>_add_list', array('content' => $content));
  }

}


/**
 * Form callback wrapper: create or edit a <%= moduleName %>.
 *
 * @param $<%= moduleName %>
 *   The <%= moduleName %> object being edited by this form.
 *
 * @see <%= moduleName %>_edit_form()
 */
function <%= moduleName %>_form_wrapper($<%= moduleName %>) {
  // Add the breadcrumb for the form's location.
  <%= moduleName %>_set_breadcrumb();
  return drupal_get_form('<%= moduleName %>_edit_form', $<%= moduleName %>);
}


/**
 * Form callback wrapper: delete a <%= moduleName %>.
 *
 * @param $<%= moduleName %>
 *   The <%= moduleName %> object being edited by this form.
 *
 * @see <%= moduleName %>_edit_form()
 */
function <%= moduleName %>_delete_form_wrapper($<%= moduleName %>) {
  // Add the breadcrumb for the form's location.
  //<%= moduleName %>_set_breadcrumb();
  return drupal_get_form('<%= moduleName %>_delete_form', $<%= moduleName %>);
}


/**
 * Form callback: create or edit a <%= moduleName %>.
 *
 * @param $<%= moduleName %>
 *   The <%= moduleName %> object to edit or for a create form an empty <%= moduleName %> object
 *     with only a <%= moduleName %> type defined.
 */
function <%= moduleName %>_edit_form($form, &$form_state, $<%= moduleName %>) {
  // Add the default field elements.
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('<%= className %> Name'),
    '#default_value' => isset($<%= moduleName %>->name) ? $<%= moduleName %>->name : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  $form['data']['#tree'] = TRUE;
  $form['data']['sample_data'] = array(
    '#type' => 'checkbox',
    '#title' => t('An interesting <%= moduleName %> switch'),
    '#default_value' => isset($<%= moduleName %>->data['sample_data']) ? $<%= moduleName %>->data['sample_data'] : 1,
  );

  // Add the field related form elements.
  $form_state['<%= moduleName %>'] = $<%= moduleName %>;
  field_attach_form('<%= moduleName %>', $<%= moduleName %>, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save <%= moduleName %>'),
    '#submit' => $submit + array('<%= moduleName %>_edit_form_submit'),
  );

  if (!empty($<%= moduleName %>->name)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete <%= moduleName %>'),
      '#suffix' => l(t('Cancel'), 'admin/content/<%= moduleName %>s'),
      '#submit' => $submit + array('<%= moduleName %>_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = '<%= moduleName %>_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the <%= moduleName %> form
 */
function <%= moduleName %>_edit_form_validate(&$form, &$form_state) {
  $<%= moduleName %> = $form_state['<%= moduleName %>'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('<%= moduleName %>', $<%= moduleName %>, $form, $form_state);
}


/**
 * Form API submit callback for the <%= moduleName %> form.
 *
 * @todo remove hard-coded link
 */
function <%= moduleName %>_edit_form_submit(&$form, &$form_state) {

  $<%= moduleName %> = entity_ui_controller('<%= moduleName %>')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the <%= moduleName %> and go back to the list of <%= moduleName %>s

  // Add in created and changed times.
  if ($<%= moduleName %>->is_new = isset($<%= moduleName %>->is_new) ? $<%= moduleName %>->is_new : 0){
    $<%= moduleName %>->created = time();
  }

  $<%= moduleName %>->changed = time();

  $<%= moduleName %>->save();
  $form_state['redirect'] = 'admin/content/<%= moduleName %>s';
}

/**
 * Form API submit callback for the delete button.
 *
 * @todo Remove hard-coded path
 */
function <%= moduleName %>_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/<%= moduleName %>s/<%= moduleName %>/' . $form_state['<%= moduleName %>']-><%= moduleName %>_id . '/delete';
}


/**
 * Form callback: confirmation form for deleting a <%= moduleName %>.
 *
 * @param $<%= moduleName %>
 *   The <%= moduleName %> to delete
 *
 * @see confirm_form()
 */
function <%= moduleName %>_delete_form($form, &$form_state, $<%= moduleName %>) {
  $form_state['<%= moduleName %>'] = $<%= moduleName %>;

  $form['#submit'][] = '<%= moduleName %>_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete <%= moduleName %> %name?', array('%name' => $<%= moduleName %>->name)),
    'admin/content/<%= moduleName %>s/<%= moduleName %>',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for <%= moduleName %>_delete_form
 */
function <%= moduleName %>_delete_form_submit($form, &$form_state) {
  $<%= moduleName %> = $form_state['<%= moduleName %>'];

  <%= moduleName %>_delete($<%= moduleName %>);

  drupal_set_message(t('The <%= moduleName %> %name has been deleted.', array('%name' => $<%= moduleName %>->name)));
  watchdog('<%= moduleName %>', 'Deleted <%= moduleName %> %name.', array('%name' => $<%= moduleName %>->name));

  $form_state['redirect'] = 'admin/content/<%= moduleName %>s';
}



/**
 * Page to add <%= className %> Entities.
 *
 * @todo Pass this through a proper theme function
 */
function <%= moduleName %>_add_page() {
  $controller = entity_ui_controller('<%= moduleName %>');
  return $controller->addPage();
}


/**
 * Displays the list of available <%= moduleName %> types for <%= moduleName %> creation.
 *
 * @ingroup themeable
 */
function theme_<%= moduleName %>_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="<%= moduleName %>-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer <%= moduleName %> types')) {
      $output = '<p>' . t('<%= className %> Entities cannot be added because you have not created any <%= moduleName %> types yet. Go to the <a href="@create-<%= moduleName %>-type"><%= moduleName %> type creation page</a> to add a new <%= moduleName %> type.', array('@create-<%= moduleName %>-type' => url('admin/structure/<%= moduleName %>_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No <%= moduleName %> types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}





/**
 * Sets the breadcrumb for administrative <%= moduleName %> pages.
 */
function <%= moduleName %>_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('<%= className %>s'), 'admin/content/<%= moduleName %>s'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
