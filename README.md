# Generator-drupalentities

Yeoman generator for generating a Drupal 7 entity boilerplate code.

## Motivation

I wanted to automate away the boring parts in creating a Drupal entity. Current options were:

1. use [ECK](https://www.drupal.org/project/eck)
2. Adopt [model](https://www.drupal.org/project/model) and customize it to your own needs.

I prefer the latter approach. I like my entities in code, rather than have it as a feature. ECK [prefers it too](https://www.drupal.org/node/1971326#comment-7307660).

## Getting started
- Make sure you have [yo](https://github.com/yeoman/yo) installed:
    `npm install -g yo`
- Install the generator: `npm install -g generator-drupalentities`
- mkdir your module folder at sites/*/modules and cd into it
- Run: `yo drupalentities`

## Todo
1. option to support revisions.
2. switch bundles on or off for an entity.
3. add more properties to an entity.

## License
[MIT License](http://en.wikipedia.org/wiki/MIT_License)

Let me know if it works for you, love to hear feedback, bug reports etc. [Contact](https://twitter.com/lakshminp).
