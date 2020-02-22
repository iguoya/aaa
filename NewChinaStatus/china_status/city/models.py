from django.db import models

# Create your models here.
class GDP(models.Model):

    city = models.CharField(verbose_name='城市', max_length=50)
    amount = models.DecimalField(verbose_name='GDP（亿）', max_digits=7,  decimal_places=2, blank=True, null=True)
    population = models.DecimalField(verbose_name='年初人口（万）', max_digits=6,  decimal_places=2, blank=True, null=True)
    per_gdp = models.IntegerField(verbose_name='人均GDP（元）', blank=True, null=True)

    increase_amount = models.DecimalField(verbose_name='增量（亿）', max_digits=6,  decimal_places=2, blank=True, null=True)
    increase_rate = models.DecimalField(verbose_name='名义增速', max_digits=5, decimal_places=2, blank=True,
                                              null=True)
    year = models.IntegerField(verbose_name='年份', blank=True, null=True, default=2017)

    def __unicode__(self):
        return self.year + self.city

    class Meta:
        verbose_name = "地级市"
        verbose_name_plural = "地级市GDP排名"
        ordering = ['-amount']