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
            expect(Curl.get('http://127.0.0.1:8888/servats_off').response_code).to eq(404)
        end
        it 'should be on and respond with 200 @ /servats_on' do
            expect(Curl.get('http://127.0.0.1:8888/servats_on').response_code).to eq(200)
        end
        it 'should be on and respond with 200 @ /servats_user_theme' do
            expect(Curl.get('http://127.0.0.1:8888/servats_user_theme').response_code).to eq(200)
        end
    end
    describe 'Module Response Content' do
        it 'should contain module header' do
            expect(Curl.get('http://127.0.0.1:8888/servats_on').body).to include("Nginx Server Status")
        end
        it 'should contain the correct module version' do
            expect(Curl.get('http://127.0.0.1:8888/servats_on').body).to include("HTTP Servats Module/1.0.0-alpha2")
        end
        it 'should contain active connections of 1' do
            expect(Curl.get('http://127.0.0.1:8888/servats_user_theme').body).to include("<h3>Workers</h3>");
        end
        it 'should contain workers' do
            expect(Curl.get('http://127.0.0.1:8888/servats_user_theme').body).to include("<h3>Requests Over Time</h3>");
        end
    end
end

# EOF
