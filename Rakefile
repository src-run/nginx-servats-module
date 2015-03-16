##
 # Rakefile
 #
 # This file is part of the HTTP Servats Module.
 #
 # For the full copyright and license information, please view the LICENSE.md
 # file that was distributed with this source code.
 #
 ##

require 'rake'
require 'rspec/core/rake_task'

RSpec::Core::RakeTask.new(:integration) do |t|
    t.pattern = 'spec/**/*_spec.rb'
end

namespace :nginx do
    desc 'Starts Nginx web server.'
    task :start do
        `build/sbin/nginx`
        sleep 1
    end

    desc 'Stops Nginx web server.'
    task :stop do
        `build/sbin/nginx -s stop`
    end

    desc 'Re-compiles Nginx from source.'
    task :'compile' do
        sh 'scripts/make.bash all'
    end

    desc 'Clean Nginx source.'
    task :'clean' do
        sh 'scripts/make.bash clean'
    end
end

desc 'Run tests'
task :test => ['nginx:start', :integration, 'nginx:stop']

desc 'Run tests on fresh compile'
task :compile_and_test => ['nginx:compile', :test]

desc 'Default is to run tests'
task :default => [:test]

# EOF
