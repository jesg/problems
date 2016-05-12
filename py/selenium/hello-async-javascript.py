from __future__ import print_function
from selenium import webdriver as wd

driver = wd.Chrome()

driver.get('http://www.jquery-tutorial.net/introduction/hello-world')
print(driver.title)

driver.set_script_timeout(30)
result = driver.execute_async_script("""
    var done = arguments[0];
    $(window).one('mouseenter', function() { done(10); });
"""
)
print(result)
# should be 10

driver.quit()
