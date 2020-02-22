# Create your models here.
from django.db import models

# Create your models here.
class ResidentIncome(models.Model):

    province = models.CharField(verbose_name='省份', max_length=50)
    total = models.IntegerField(verbose_name='总体收入', )
    total_increase_rate = models.DecimalField(verbose_name='总体增速', max_digits=3,  decimal_places=1, blank=True, null=True)
    city = models.IntegerField(verbose_name='城镇收入', blank=True, null=True)
    city_increase_rate = models.DecimalField(verbose_name='城镇增速', max_digits=3,  decimal_places=1, blank=True, null=True)
    rural = models.IntegerField(verbose_name='农村收入', blank=True, null=True)
    rural_increase_rate = models.DecimalField(verbose_name='农村增速', max_digits=3,  decimal_places=1, blank=True, null=True)
    total_increase = models.IntegerField(verbose_name='全体增量', blank=True, null=True)
    city_increase = models.IntegerField(verbose_name='城镇增量', blank=True, null=True)
    rural_increase = models.IntegerField(verbose_name='农村增量', blank=True, null=True)
    year = models.IntegerField(verbose_name='年份', blank=True, null=True, default=2017)

    def __unicode__(self):
        return self.year + self.province

    class Meta:
        verbose_name = "省级数据"
        verbose_name_plural = "中国大陆省级全体居民收入排名"
        ordering = ['-total']