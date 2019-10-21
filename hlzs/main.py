#!/usr/bin/python3
from selenium import webdriver # 从selenium导入webdriver

browser = webdriver.Chrome()  # Optional argument, if not specified will search path.
browser.get('https://www.hulizhushou.com/client/qa_pro/149167?access_token=39za5427pzlolyb3py') # 获取百度页面