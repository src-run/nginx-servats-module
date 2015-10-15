##
 # integration_spec.rb
 #
 # This file is part of the HTTP Servats Module.
 #
 # For the full copyright and license information, please view the LICENSE.md
 # file that was distributed with this source code.
 #
 ##

require 'spec_helper'

describe 'Basic Integration Specs' do
    describe 'Bootstrap Nginx' do
        it 'server should be running on localhost, port 8765' do
            expect(Curl.get('http://127.0.0.1:8765').response_code).to eq(200)
        end
        it 'server should respond with default welcome page' do
            expect(Curl.get('http://127.0.0.1:8765').body).to include("Welcome to nginx!")
        end
    end
end

# EOF
