<?php

/**
 * @file
 * Providing extra functionality for the <%= className %> UI via views.
 */


/**
 * Implements hook_views_data()
 */
function <%= moduleName %>_views_data_alter(&$data) {
  $data['<%= moduleName %>']['link_<%= moduleName %>'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the <%= moduleName %>.'),
      'handler' => '<%= moduleName %>_handler_link_field',
    ),
  );
  $data['<%= moduleName %>']['edit_<%= moduleName %>'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the <%= moduleName %>.'),
      'handler' => '<%= moduleName %>_handler_edit_link_field',
    ),
  );
  $data['<%= moduleName %>']['delete_<%= moduleName %>'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the <%= moduleName %>.'),
      'handler' => '<%= moduleName %>_handler_delete_link_field',
    ),
  );
  // This content of this field are decided based on the menu structure that
  // follows <%= moduleName %>s/<%= moduleName %>/%<%= moduleName %>_id/op
  $data['<%= moduleName %>']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this <%= moduleName %>.'),
      'handler' => '<%= moduleName %>_handler_<%= moduleName %>_operations_field',
    ),
  );
}


/**
 * Implements hook_views_default_views().
 */
function <%= moduleName %>_views_default_views() {
  $views = array();

  $view = new view;
  $view->name = '<%= moduleName %>s';
  $view->description = 'A list of all <%= moduleName %>s';
  $view->tag = '<%= moduleName %>s';
  $view->base_table = '<%= moduleName %>';
  $view->human_name = '<%= className %>s';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '<%= className %>s';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create any <%= moduleName %> type';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    '<%= moduleName %>_id' => '<%= moduleName %>_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    '<%= moduleName %>_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty ';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No <%= moduleName %>s have been created yet';
  /* Field: <%= className %>: <%= className %> ID */
  $handler->display->display_options['fields']['<%= moduleName %>_id']['id'] = '<%= moduleName %>_id';
  $handler->display->display_options['fields']['<%= moduleName %>_id']['table'] = '<%= moduleName %>';
  $handler->display->display_options['fields']['<%= moduleName %>_id']['field'] = '<%= moduleName %>_id';
  $handler->display->display_options['fields']['<%= moduleName %>_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['<%= moduleName %>_id']['empty_zero'] = 0;
  /* Field: <%= className %>: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = '<%= moduleName %>';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  /* Field: <%= className %>: Link */
  $handler->display->display_options['fields']['link_<%= moduleName %>']['id'] = 'link_<%= moduleName %>';
  $handler->display->display_options['fields']['link_<%= moduleName %>']['table'] = '<%= moduleName %>';
  $handler->display->display_options['fields']['link_<%= moduleName %>']['field'] = 'link_<%= moduleName %>';
  $handler->display->display_options['fields']['link_<%= moduleName %>']['label'] = 'View';
  $handler->display->display_options['fields']['link_<%= moduleName %>']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['alter']['external'] = 0;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['alter']['html'] = 0;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['hide_empty'] = 0;
  $handler->display->display_options['fields']['link_<%= moduleName %>']['empty_zero'] = 0;
  /* Field: <%= className %>: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = '<%= moduleName %>';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', '<%= moduleName %>s_admin_page');
  $handler->display->display_options['path'] = 'admin/content/<%= url %>s/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = '<%= className %>s';
  $handler->display->display_options['tab_options']['description'] = 'Manage <%= moduleName %>s';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['<%= moduleName %>s'] = array(
    t('Master'),
    t('<%= className %>s'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Empty '),
    t('No <%= moduleName %>s have been created yet'),
    t('<%= className %> ID'),
    t('.'),
    t(','),
    t('Name'),
    t('View'),
    t('Operations links'),
    t('Page'),
  );
  $views[] = $view;
  return $views;

}
