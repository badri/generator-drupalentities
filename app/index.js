'use strict';
var util = require('util');
var path = require('path');
var yeoman = require('yeoman-generator');
var yosay = require('yosay');
var chalk = require('chalk');

var DrupalEntityGenerator = module.exports = function DrupalEntityGenerator(args, options, config) {
  yeoman.generators.Base.apply(this, arguments);
  this.moduleName = path.basename(process.cwd());

  this.on('end', function () {
    this.installDependencies({ skipInstall: true });
  });

  this.capitalize = function(string) {
	return string.charAt(0).toUpperCase() + string.slice(1);
  }
};

util.inherits(DrupalEntityGenerator, yeoman.generators.Base);

DrupalEntityGenerator.prototype.askFor = function askFor() {
  var cb = this.async();


  // TODO: add support for list of properties to be added to entity
    // 1. path url - ?
    // 2. pluralized string
    // 3. class name
    // 4. controller name - ?

  var prompts = [{
    name: 'moduleNamePrompt',
    message: 'What is the name of your module:',
    default: this.moduleName
  },{
    name: 'moduleDesc',
    message: 'Describe your module:'
  },{
    name: 'modulePackage',
    message: 'Provide a module package:',
    default: 'Custom'
  },{
    name: 'moduleDepend',
    message: 'What are your module\'s dependenies? (space seperated)'
  },{
    name: 'label',
    message: 'What is your entity label?',
    default: this.capitalize(this.moduleName)
  },{
    name: 'className',
    message: 'entity class name?',
    default: this.capitalize(this.moduleName)
  },{
    name: 'pluralizedName',
    message: 'entity plurlized name?',
    default: this.moduleName + 's'
  },{
    name: 'entityId',
    message: 'entity id name?',
    default: this.moduleName + '_id'
  },{
    name: 'url',
    message: 'entity base url?',
    default: this.moduleName
  },{
    type: 'confirm',
    name: 'revisions',
    message: 'Does your entity support revisions?',
    default: false
  },{
    type: 'confirm',
    name: 'views',
    message: 'Do you want to add views support for your entity?',
    default: false
  },{
    type: 'confirm',
    name: 'bundles',
    message: 'Will your entity be having bundles?',
    default: true
  },{
    type: 'confirm',
    name: 'fieldable',
    message: 'Is your entity fieldable?',
    default: true
  },{
    type: 'confirm',
    name: 'license',
    message: 'add GPL2 license?',
    default: false
  }];

  this.prompt(prompts, function (props) {
    this.moduleName = props.moduleNamePrompt;
    this.moduleDesc = props.moduleDesc;
    this.modulePackage = props.modulePackage;
    this.dependencies = props.moduleDepend.length !== 0 ? 'dependencies[] = ' + props.moduleDepend.split(' ').join('\ndependencies[] = ') : '';
    this.entityLabel = props.label;
    this.className = props.className;
    this.pluralizedName = props.pluralizedName;
    this.entityId = props.entityId;
    this.url = props.url;
    this.revisions = props.revisions;
    this.views = props.views;
    this.bundles = props.bundles;
    this.fieldable = props.fieldable;
    this.license = props.license;

    cb();
  }.bind(this));
};

DrupalEntityGenerator.prototype.app = function app() {
  var mn = this.moduleName;

  this.template('_template.info', mn + '.info');
  this.template('_template.install', mn + '.install');
  this.template('_template.module', mn + '.module');

  this.template('_template.tpl.php', mn + '.tpl.php');
  this.template('_template-sample-data.tpl.php', mn + '-sample-data.tpl.php');

  this.template('_template.admin.inc', mn + '.admin.inc');
  this.template('_template_type.admin.inc', mn + '_type.admin.inc');

  if(this.views) {
    this.template('views/_template.views.inc', 'views/' + mn + '.views.inc');
    this.template('views/_template_handler_template_operations_field.inc', 'views/' + mn + '_handler_' + mn + '_operations_field.inc');
    this.template('views/_template_handler_link_field.inc', 'views/' + mn + '_handler_link_field.inc');
    this.template('views/_template_handler_edit_link_field.inc', 'views/' + mn + '_handler_edit_link_field.inc');
    this.template('views/_template_handler_delete_link_field.inc', 'views/' + mn + '_handler_delete_link_field.inc');
  }
  if(this.license) {
    this.copy('LICENSE.txt', 'LICENSE.txt');
  }
};
