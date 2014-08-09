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
    this.installDependencies({ skipInstall: options['skip-install'] });
  });

  this.capitalize = function(string) {
	return string.charAt(0).toUpperCase() + string.slice(1);
  }
};

util.inherits(DrupalEntityGenerator, yeoman.generators.Base);

DrupalEntityGenerator.prototype.askFor = function askFor() {
  var cb = this.async();


  // TODO: add support for list of properties to be added to entity
  var prompts = [{
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
    name: 'revisions',
    message: 'Does your entity support revisions?',
    default: 'Y/n'
  },{
    name: 'views',
    message: 'Do you want to add views support for your entity?',
    default: 'Y/n'
  },{
    name: 'bundles',
    message: 'Will your entity be having bundles?',
    default: 'Y/n'
  },{
    name: 'fieldable',
    message: 'Is your entity fieldable?',
    default: 'Y/n'
  },{
    name: 'license',
    message: 'add GPL2 license?',
    default: 'Y/n'
  }];

  this.prompt(prompts, function (err, props) {
    if (err) {
      return this.emit('error', err);
    }

    this.moduleDesc = props.moduleDesc;
    this.modulePackage = props.modulePackage;
    this.dependencies = props.moduleDepend.length !== 0 ? 'dependencies[] = ' + props.moduleDepend.split(' ').join('\r\ndependencies[] = ') : '';
    this.revisions = props.revisions;
    this.entityLabel = props.label;
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

  this.template('_template.admin.inc', mn + '.admin.inc');
  this.template('_template_type.admin.inc', mn + '_type.admin.inc');

  this.copy('LICENSE', 'LICENSE');

};
