##
 # servats_spec.rb
 #
 # This file is part of the HTTP Servats Module.
 #
 # For the full copyright and license information, please view the LICENSE.md
 # file that was distributed with this source code.
 #
 ##

require 'spec_helper'

describe 'Servats Module Specs' do
    describe 'Module Response Codes' do
        it 'should be off and respond with 404 @ /servats_off' do
            expect(Curl.get('http://127.0.0.1:8765/servats_off').response_code).to eq(404)
        end
        it 'should be on and respond with 200 @ /servats_on' do
            expect(Curl.get('http://127.0.0.1:8765/servats_on').response_code).to eq(200)
        end
        it 'should be on and respond with 200 @ /servats_user_theme' do
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme').response_code).to eq(200)
        end
    end
    describe 'Module Response Content (Standard Config)' do
        it 'should contain module header' do
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include("Nginx Server Status")
        end
        it 'should contain the correct module version' do
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include("HTTP Servats Module/1.0.0-beta2")
        end
        it 'should contain active connections of 1' do
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include("<dt>Active Connections</dt>\n                    <dd>1</dd>");
        end
        it 'should contain overview content block' do
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include("<h3>Overview</h3>");
        end
        it 'should contain requests states content block' do
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include("<h3>Request States</h3>");
        end
        it 'should contain workers content block' do
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include("<h3>Workers</h3>");
        end
        it 'should contain requests over time content block' do
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include("<h3>Requests Over Time</h3>");
        end
        it 'should contain requests content block' do
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include("<h3>Connections</h3>");
        end
        it 'should have internal stylesheets' do
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include('<link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css">');
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include('<link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap-theme.min.css">');
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include('<link rel="stylesheet" href="//fonts.googleapis.com/css?family=Bitter:400,400italic|Source+Sans+Pro:300,400,600,300italic,400italic|Ubuntu+Mono:400,700,400italic|Roboto+Condensed:300italic,400italic,700,300,400">');
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include('$(window).load(function(){');
        end
        it 'should have internal scripts' do
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include('<script src="//ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>');
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include('<script src="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/js/bootstrap.min.js"></script>');
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include('<script src="//cdnjs.cloudflare.com/ajax/libs/Chart.js/1.0.2/Chart.min.js"></script>');
            expect(Curl.get('http://127.0.0.1:8765/servats_on').body).to include('<style type="text/css">');
        end
    end
    describe 'Module Response Content (User Theme Config)' do
        it 'should contain user stylesheet' do
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme').body).to include("/some/path/to/stylesheet.css")
        end
        it 'should contain user js library include' do
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme').body).to include("/some/path/to/lib.js")
        end
        it 'should contain user js main include' do
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme').body).to include("/some/path/to/main.js");
        end
        it 'should have internal stylesheets' do
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme').body).to include('<link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css">');
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme').body).to include('<link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap-theme.min.css">');
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme').body).to include('<link rel="stylesheet" href="//fonts.googleapis.com/css?family=Bitter:400,400italic|Source+Sans+Pro:300,400,600,300italic,400italic|Ubuntu+Mono:400,700,400italic|Roboto+Condensed:300italic,400italic,700,300,400">');
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme').body).to include('$(window).load(function(){');
        end
        it 'should have internal scripts' do
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme').body).to include('<script src="//ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>');
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme').body).to include('<script src="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/js/bootstrap.min.js"></script>');
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme').body).to include('<script src="//cdnjs.cloudflare.com/ajax/libs/Chart.js/1.0.2/Chart.min.js"></script>');
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme').body).to include('<style type="text/css">');
        end
    end
    describe 'Module Response Content (User Theme Only Config)' do
        it 'should contain user stylesheet' do
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme_only').body).to include("/some/path/to/stylesheet.css")
        end
        it 'should contain user js library include' do
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme_only').body).to include("/some/path/to/lib.js")
        end
        it 'should contain user js main include' do
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme_only').body).to include("/some/path/to/main.js");
        end
        it 'should not have internal stylesheets' do
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme_only').body).not_to include('<link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap.min.css">');
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme_only').body).not_to include('<link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/css/bootstrap-theme.min.css">');
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme_only').body).not_to include('<link rel="stylesheet" href="//fonts.googleapis.com/css?family=Bitter:400,400italic|Source+Sans+Pro:300,400,600,300italic,400italic|Ubuntu+Mono:400,700,400italic|Roboto+Condensed:300italic,400italic,700,300,400">');
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme_only').body).not_to include('<style type="text/css">');
        end
        it 'should not have internal scripts' do
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme_only').body).not_to include('<script src="//ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>');
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme_only').body).not_to include('<script src="//maxcdn.bootstrapcdn.com/bootstrap/3.3.2/js/bootstrap.min.js"></script>');
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme_only').body).not_to include('<script src="//cdnjs.cloudflare.com/ajax/libs/Chart.js/1.0.2/Chart.min.js"></script>');
            expect(Curl.get('http://127.0.0.1:8765/servats_user_theme_only').body).not_to include('<style type="text/css">');
        end
    end
end

# EOF
