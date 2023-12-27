#ifndef __SOC_ROCKCHIP_IOMMU_H
#define __SOC_ROCKCHIP_IOMMU_H

struct device;
struct iommu_domain;
struct iommu_iotlb_gather;
struct platform_device;

/* 1. dev and pdev is iommu device.
 * 2. store third_iommu data in dev->platform_data.
 */
struct third_iommu_ops_wrap {
	int (*attach_dev)(struct iommu_domain *domain, struct device *dev);
	void (*detach_dev)(struct iommu_domain *domain, struct device *dev);
	int (*map)(struct iommu_domain *domain, unsigned long iova,
		   phys_addr_t paddr, size_t size, int prot, gfp_t gfp,
		   struct device *dev);
	size_t (*unmap)(struct iommu_domain *domain, unsigned long iova,
			size_t size, struct iommu_iotlb_gather *iotlb_gather,
			struct device *dev);
	void (*flush_iotlb_all)(struct iommu_domain *domain,
				struct device *dev);
	phys_addr_t (*iova_to_phys)(struct iommu_domain *domain,
				    dma_addr_t iova, struct device *dev);
	void (*free)(struct iommu_domain *domain, struct device *dev);
	int (*enable)(struct device *dev);
	int (*disable)(struct device *dev);
	void (*shutdown)(struct platform_device *pdev);
	int (*suspend)(struct device *dev);
	int (*resume)(struct device *dev);
	int (*probe)(struct platform_device *pdev);
};

int rockchip_iommu_enable(struct device *dev);
int rockchip_iommu_disable(struct device *dev);
int rockchip_iommu_force_reset(struct device *dev);
void rockchip_iommu_mask_irq(struct device *dev);
void rockchip_iommu_unmask_irq(struct device *dev);

#endif
