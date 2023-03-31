import multiprocessing as mp
from time import time
import logging
import requests
from multiprocessing.pool import Pool

WEBSITE_LIST = [
    "http://amazon.co.uk",
    "http://amazon.com",
    "http://facebook.com",
    "http://google.com",
    "http://google.fr",
    "http://google.es",
    "http://google.co.uk",
    "http://gmail.com",
    "http://stackoverflow.com",
    "http://github.com",
    "http://heroku.com",
    "http://really-cool-available-domain.com",
    "http://djangoproject.com",
    "http://rubyonrails.org",
    "http://basecamp.com",
    "http://trello.com",
    "http://shopify.com",
    "http://another-really-interesting-domain.co",
    "http://airbnb.com",
    "http://instagram.com",
    "http://snapchat.com",
    "http://youtube.com",
    "http://baidu.com",
    "http://yahoo.com",
    "http://live.com",
    "http://linkedin.com",
    "http://netflix.com",
    "http://wordpress.com",
    "http://bing.com",
]


class WebsiteDownException(Exception):
    pass


def ping_website(address, timeout=20):
    """
    Check if a website is down. A website is considered down
    if either the status_code >= 400 or if the timeout expires

    Throw a WebsiteDownException if any of the website down conditions are met
    """
    try:
        response = requests.head(address, timeout=timeout)
        if response.status_code >= 400:
            logging.warning(
                "Website %s returned status_code=%s" % (address, response.status_code)
            )
            raise WebsiteDownException()
    except requests.exceptions.RequestException:
        logging.warning("Timeout expired for website %s" % address)
        raise WebsiteDownException()


def check_website(address):
    """
    Utility function: check if a website is down, if so, notify the user
    """
    try:
        ping_website(address)
    except WebsiteDownException:
        print("The websie " + address + " is down")

def multiprocess_website_uptimer(WEBSITE_LIST, NUM_PROCESSES):
    # Set up timer and partial function
    ts = time()

    # Use process pool with partial func / website lists being passed to pool
    with Pool(NUM_PROCESSES) as p:
        p.map(check_website, WEBSITE_LIST)

    # Output results
    print("Took {}s".format(time() - ts))

if __name__ == "__main__":
    NUM_PROCESSES = 4
    multiprocess_website_uptimer(WEBSITE_LIST, NUM_PROCESSES)
